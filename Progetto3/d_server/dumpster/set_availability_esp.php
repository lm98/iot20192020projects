<?php
include 'db_helper.php';

//questo e' il formato del file json
$json = '{"avail":1/0,"pass":"pass"}';
$json = file_get_contents('php://input');
//$json = '{"avail":0,"pass":"password"}';
$decoded= json_decode($json);
if (check_pass($decoded->pass)){
    set_avail($decoded->avail);
    http_response_code(200);
}else{
    http_response_code(418);
}