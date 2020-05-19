<?php
include 'db_helper.php';

$json = file_get_contents('php://input');

deposit_fix($json);
if (clean_empty_rows()){
    http_response_code(200);    
}
?>
