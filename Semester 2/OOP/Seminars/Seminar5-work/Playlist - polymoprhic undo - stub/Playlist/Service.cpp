#include "Service.h"
#include <algorithm>
#include "FilePlaylist.h"
#include "RepositoryExceptions.h"

using namespace std;

void Service::addSongToRepository(const std::string& artist, const std::string& title, double minutes, double seconds, const std::string& source)
{
	Song s{ artist, title, Duration{minutes, seconds}, source };
	this->validator.validate(s);
	this->repo.addSong(s);

	this->redoActions.clear();
	unique_ptr<Action> action = make_unique<ActionAdd>( this->repo, s );
	this->undoActions.push_back(std::move(action));
}

void Service::removeSongFromRepository(const std::string & artist, const std::string & title)
{
	Song s = this->repo.findByArtistAndTitle(artist, title);
	this->repo.removeSong(s);

	this->redoActions.clear();
	unique_ptr<Action> action = make_unique<ActionRemove>(this->repo, s);
	this->undoActions.push_back(std::move(action));
}

void Service::updateSong(const std::string& oldArtist, const std::string& oldTitle, const std::string& artist, const std::string& title, double minutes, double seconds, const std::string& source)
{
	Song oldSong = this->repo.findByArtistAndTitle(oldArtist, oldTitle);
	Song newSong{ artist, title, Duration{minutes, seconds}, source };
	this->validator.validate(newSong);
	this->repo.updateSong(oldSong, newSong);

	this->redoActions.clear();
	unique_ptr<Action> action = make_unique<ActionUpdate>(this->repo, oldSong, newSong);
	this->undoActions.push_back(std::move(action));
}

void Service::undo()
{
	if (this->undoActions.empty())
		throw RepositoryException("No more undos!");

	unique_ptr<Action> action = std::move(this->undoActions.back());
	action->executeUndo();
	this->redoActions.push_back(std::move(action));
	this->undoActions.pop_back();
}

void Service::redo()
{
	if (this->redoActions.empty())
		throw RepositoryException("No more redos!");

	unique_ptr<Action> action = std::move(this->redoActions.back());
	action->executeRedo();
	this->undoActions.push_back(std::move(action));
	this->redoActions.pop_back();
}

void Service::addSongToPlaylist(const Song& song)
{
	if (this->playList == nullptr)
		return;
	this->playList->add(song);
}

void Service::addAllSongsByArtistToPlaylist(const std::string& artist)
{
	vector<Song> songs = this->repo.getSongs();
	int nSongs = static_cast<int>(count_if(songs.begin(), songs.end(),
		[artist](const Song& s)
		{
			return s.getArtist() == artist;
		}));

	vector<Song> songsByArtist(nSongs);
	copy_if(songs.begin(), songs.end(), songsByArtist.begin(),
		[artist](const Song& s)
		{
			return s.getArtist() == artist;
		});

	for (auto s : songsByArtist)
		this->playList->add(s);
}

void Service::startPlaylist()
{
	if (this->playList == nullptr)
		return;
	this->playList->play();
}

void Service::nextSongPlaylist()
{
	if (this->playList == nullptr)
		return;
	this->playList->next();
}

void Service::savePlaylist(const std::string& filename)
{
	if (this->playList == nullptr)
		return;

	this->playList->setFilename(filename);
	this->playList->writeToFile();
}

void Service::openPlaylist() const
{
	if (this->playList == nullptr)
		return;

	this->playList->displayPlaylist();
}
