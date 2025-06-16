<?php
require 'db.php';

header('Access-Control-Allow-Origin: http://localhost:4200');
header('Access-Control-Allow-Credentials: true');

$category = $_GET['category'] ?? null;
$start = $_GET['start'] ?? null;
$end = $_GET['end'] ?? null;

$sql = "SELECT * FROM news WHERE 1=1";
$params = [];
$types = '';

if ($category) {
    $sql .= " AND category = ?";
    $params[] = $category;
    $types .= 's';
}
if ($start) {
    $sql .= " AND date >= ?";
    $params[] = $start;
    $types .= 's';
}
if ($end) {
    $sql .= " AND date <= ?";
    $params[] = $end;
    $types .= 's';
}

$stmt = $conn->prepare($sql);

if ($params) {
    $stmt->bind_param($types, ...$params);
}

$stmt->execute();
$result = $stmt->get_result();

$news = [];
while ($row = $result->fetch_assoc()) {
    $news[] = $row;
}

echo json_encode($news);
$stmt->close();
$conn->close();