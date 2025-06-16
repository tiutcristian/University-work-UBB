<?php
header('Access-Control-Allow-Origin: http://localhost:4200');
header('Access-Control-Allow-Credentials: true');
header('Access-Control-Allow-Headers: Content-Type, Authorization');
header('Access-Control-Allow-Methods: GET, POST, OPTIONS');
header('Content-Type: application/json');

require 'db.php';

$id = $_GET['id'];
$stmt = $conn->prepare("SELECT * FROM news WHERE id = ?");
$stmt->bind_param('i', $id);
$stmt->execute();
$result = $stmt->get_result();
$news = $result->fetch_assoc();

if ($news) {
    echo json_encode($news);
} else {
    echo json_encode(['error' => 'News not found']);
}
$stmt->close();
$conn->close();