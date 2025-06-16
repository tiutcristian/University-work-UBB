<?php
header('Access-Control-Allow-Origin: http://localhost:4200');
header('Access-Control-Allow-Credentials: true');
header('Access-Control-Allow-Headers: Content-Type, Authorization');
header('Access-Control-Allow-Methods: GET, POST, OPTIONS');
header('Content-Type: application/json');

if ($_SERVER['REQUEST_METHOD'] === 'OPTIONS') {
    http_response_code(200);
    exit();
}

require 'db.php';

$json = file_get_contents('php://input');
$data = json_decode($json);

$id = $data->id;
$title = $data->title;
$text = $data->text;
$producer = $data->producer;
$date = $data->date;
$category = $data->category;

$stmt = $conn->prepare("UPDATE news SET title=?, text=?, producer=?, date=?, category=? WHERE id=?");
$stmt->bind_param('sssssi', $title, $text, $producer, $date, $category, $id);
$stmt->execute();

if ($stmt->affected_rows > 0) {
    echo json_encode(array("status" => "success", "message" => "News updated successfully"));
} else {
    echo json_encode(array("status" => "error", "message" => "Failed to update news"));
}
$stmt->close();
$conn->close();