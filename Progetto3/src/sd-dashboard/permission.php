<?php
include 'db_helper.php';

if (is_available()){
    //creo nuova riga e restituisco un token, id di deposito
    //mi passano il tipo di rifiuto con post
    //cie stato uno kambio di programaaa
    //$token = generate_token();
    
    http_response_code(200);
    //json_encode($token);    
} else {
    http_response_code(418); //i'm a teapot
    echo'not epic';
}
?>