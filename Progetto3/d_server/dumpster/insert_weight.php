<?php
include 'db_helper.php';

//ricevo il token e modifico i valori di quella riga con le letture fatte
/*$id = get_last_id();
//questo e' il formato del file json
$json = '{"a":35,"b":37,"c":43}';
success($json);
http_response_code(200);*/
$json = file_get_contents('php://input');
//echo($json);
//$logPostData = json_decode($json,true);
//echo($logPostData);
if (is_available()){
    deposit($json);
    http_response_code(200);
}else{
    http_response_code(418);
}

?>
