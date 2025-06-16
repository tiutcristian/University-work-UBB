<?php 
header('Access-Control-Allow-Origin: http://localhost:4200');
header('Access-Control-Allow-Credentials: true');

session_start();
echo json_encode(isset($_SESSION['user']));