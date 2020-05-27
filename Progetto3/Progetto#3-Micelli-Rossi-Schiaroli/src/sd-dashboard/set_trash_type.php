<?php
include 'db_helper.php';
$json = file_get_contents('php://input');
if (is_available()){
    if(set_trash_type($json)){
        echo json_encode(array("response"=>"ok"));
        http_response_code(200);
    }else{
        echo json_encode(array("response"=>"error"));
        http_response_code(418);
    }
}else{
    echo json_encode(array("response"=>"error"));
    http_response_code(418);
}

?>
