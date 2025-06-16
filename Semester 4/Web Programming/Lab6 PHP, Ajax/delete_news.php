<?php
header('Access-Control-Allow-Origin: http://localhost:4200');
header('Access-Control-Allow-Credentials: true');
header('Content-Type: application/json');
header('Access-Control-Allow-Methods: POST, OPTIONS');
header('Access-Control-Allow-Headers: Content-Type, Authorization');

require 'db.php';

$json = file_get_contents('php://input');
$data = json_decode($json);
$id = $data->id;

$stmt = $conn->prepare("DELETE FROM news WHERE id = ?");
$stmt->bind_param('i', $id);
$stmt->execute();

if ($stmt->affected_rows > 0) {
    echo json_encode(array("status" => "success", "message" => "News deleted successfully"));
} else {
    echo json_encode(array("status" => "error", "message" => "Failed to delete news"));
}

$stmt->close(); 
$conn->close();