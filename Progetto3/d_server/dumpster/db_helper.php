<?php

function db_connect() {
    $servername = "localhost";
    $username = "root";
    $password = "";
    
    // Create connection
    $conn = new mysqli($servername, $username, $password, 'dumpster');
    
    // Check connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }
    //echo "Connected successfully";
    return $conn;
}

function get_deposits(){
    $conn = db_connect();
    $sql = "SELECT deposits FROM general";
    $result = $conn->query($sql);
    
    if ($result->num_rows > 0) {
        $row = $result->fetch_assoc();
        return $row['deposits'];
    } else {
        echo "error";
    }
    $conn->close();
}

function is_available(){
    $conn = db_connect();
    $sql = "SELECT available FROM general";
    $result = $conn->query($sql);
    
    if ($result->num_rows > 0) {
        $row = $result->fetch_assoc();
        return $row['available'];
    } else {
        echo "error";
    }
    $conn->close();
}
//da togliere
function inc_depsits(){
    $conn = db_connect();

    $sql = "SELECT deposits FROM general";
    $result = $conn->query($sql);
    
    if ($result->num_rows > 0) {
        $row = $result->fetch_assoc();
    } else {
        echo "error";
    }

    $depo = $row['deposits'];
    echo $depo;
    $depo++;
    echo $depo;
    $sql = "UPDATE general SET deposits=$depo";

    if (!$conn->query($sql) === TRUE) {
        echo "Error updating record: " . $conn->error;
    }
    $conn->close();
}

function generate_token(){
    $conn = db_connect();
    //aggiungo un deposito da confermare, manca il peso dei rifiuti
    $FUUCK = "INSERT INTO deposit(a_deposited, b_deposited, c_deposited, date) VALUES (1,1,1,CURRENT_DATE)";
    $sql = "INSERT INTO 'deposit' ('a_deposited', 'b_deposited', 'c_deposited', 'date') VALUES ('1', '1', '1', CURRENT_DATE)";

    if ($conn->query($FUUCK) === TRUE) {
        //prendo l'ultimo id inserito
        $last_id = $conn->insert_id;
        $conn->close();
        return $last_id;
    } else {
        $conn->close();
        exit('error');
    } 
}

function success($jsonobj){
    $json_decoded = json_decode($jsonobj, true);
    $A = $json_decoded['a'];
    $B = $json_decoded['b'];
    $C = $json_decoded['c'];
    $id = $json_decoded['id'];
    $conn = db_connect();

    //aggiorno il deposito in attesa
    $sql = "UPDATE deposit SET a_deposited = $A, b_deposited = $B, c_deposited = $C where deposit_id = $id";
    if ($conn->query($sql) === TRUE) {
        //echo "Record updated successfully";
    } else {
        echo "Error updating record: " . $conn->error;
    }

    $wheight = $A + $B + $C;
    $sql = "SELECT weight, deposits, wheight_max FROM general";
    $result = $conn->query($sql);
    
    if ($result->num_rows > 0) {
        // output data of each row
        while($row = $result->fetch_assoc()) {
            $wheight += $row["weight"];
            $deposits = $row["deposits"];
            $wheight_max = $row["wheight_max"];
            $deposits++;

            $sql = "UPDATE general SET weight = $wheight, deposits = $deposits";

            if (!$conn->query($sql) === TRUE) {
                echo "Error updating record: " . $conn->error;
            }

            if($wheight>$wheight_max){
                $sql = "UPDATE general SET available = 0";
        
                if (!$conn->query($sql) === TRUE) {
                    exit("Error updating record: " . $conn->error);
                }
            } 
        }
        $conn->close();
    } else {
        echo "0 results";
    }
    
    
    //controls if the wheight is too much
    
}

function deposit($jsonobj){
    json_decode($jsonobj, true);
    $conn = db_connect();
    $date = date('Y-m-d');
    $A = jsonobj['a'];
    $B = jsonobj['b'];
    $C = jsonobj['c'];
    $sql = "INSERT INTO deposit (deposit_id, a_deposited, b_deposited, c_deposited, date) VALUES (NULL, $A, $B, $C, $date )";
    if (!$conn->query($sql) === TRUE) {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }

    $wheight = $A + $B + $C;
    $sql = "SELECT wheight, deposits, wheight_max FROM general";
    $result = $conn->query($sql);
    
    if ($result->num_rows > 0) {
        $row = $result->fetch_assoc();
    } else {
        exit('error');
    }
    $wheight += $row['wheight'];
    $deposits = $row['deposits'];
    $wheight_max = $row['wheight_max'];
    $deposits++;
    $sql = "UPDATE general SET wheight = $wheight, deposits = $deposits";

    if (!$conn->query($sql) === TRUE) {
        echo "Error updating record: " . $conn->error;
    }
    //controls if the wheight is too much
    if($wheight>wheight_max){
        $sql = "UPDATE general SET available = 0";

        if (!$conn->query($sql) === TRUE) {
            echo "Error updating record: " . $conn->error;
        }
    }
    $conn->close();
}

function toggle_avail(){
    $conn = db_connect();

    $sql = "SELECT available FROM general";
    $result = $conn->query($sql);
    
    if ($result->num_rows > 0) {
        $row = $result->fetch_assoc();
    } else {
        echo "error";
    }
    $avail = $row['available'] ? 0 : 1;
    $sql = "UPDATE general SET available = $avail";

    if (!$conn->query($sql) === TRUE) {
        echo "Error updating record: " . $conn->error;
    }
    
    $conn->close();
}

//solo per provare delle funzioni, da togliere
function get_last_id(){
    $conn = db_connect();

    $sql = "SELECT MAX(deposit_id) FROM deposit";
    $result = $conn->query($sql);
    
    if ($result->num_rows > 0) {
        $row = $result->fetch_row();
    } else {
        echo "error";
    }
    $id = $row[0]; 
    $conn->close();
    return $id;
}

function get_a(){
    $conn = db_connect();
    $a_trash = array();
    $sql = "SELECT a_deposited, date FROM deposit";
    $result = $conn->query($sql);
    
    if ($result->num_rows > 0) {
        while($row = $result->fetch_assoc()) {
            $A = $row["a_deposited"];
            $date = $row["date"];
            $a_trash[] = array("label"=> $date, "y"=> $A);        
        }
        $conn->close();
        return $a_trash;
    } else {
        die("error");
    }
}

function get_b(){
    $conn = db_connect();
    $b_trash = array();
    $sql = "SELECT b_deposited, date FROM deposit";
    $result = $conn->query($sql);
        
    if ($result->num_rows > 0) {
        while($row = $result->fetch_assoc()) {
            $B = $row["b_deposited"];
            $date = $row["date"];
            $b_trash[] = array("label"=> $date, "y"=> $B);        
        }
        $conn->close();
        return $b_trash;
    } else {
        die("error");
    }
}

function get_c(){
    $conn = db_connect();
    $c_trash = array();
    $sql = "SELECT c_deposited, date FROM deposit";
    $result = $conn->query($sql);
        
    if ($result->num_rows > 0) {
        while($row = $result->fetch_assoc()) {
            $C = $row["c_deposited"];
            $date = $row["date"];
            $c_trash[] = array("label"=> $date, "y"=> $C);        
        }
        $conn->close();
        return $c_trash;
    } else {
        die("error");
    }
}


?>