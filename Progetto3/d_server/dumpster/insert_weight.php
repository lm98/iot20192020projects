<?php
include 'db_helper.php';

//ricevo il token e modifico i valori di quella riga con le letture fatte
/*$id = get_last_id();
//questo e' il formato del file json
$json = '{"a":35,"b":37,"c":43,"id":15}';
success($json);
http_response_code(200);*/
if (isset($_POST["jsonobj"])){
    deposit($_POST["jsonobj"]);
    http_response_code(200);
}else{
    http_response_code(418);
}

?>