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

$title = $data->title;
$text = $data->text;
$producer = $data->producer;
$date = $data->date;
$category = $data->category;

$stmt = $conn->prepare("INSERT INTO news (title, text, producer, date, category) VALUES (?, ?, ?, ?, ?)");
$stmt->bind_param('sssss', $title, $text, $producer, $date, $category);
$stmt->execute();

if ($stmt->affected_rows > 0) {
    echo json_encode(['status' => 'success', 'message' => 'News inserted successfully']);
} else {
    echo json_encode(['status' => 'error', 'message' => 'Failed to insert news']);
}

$stmt->close();
$conn->close();