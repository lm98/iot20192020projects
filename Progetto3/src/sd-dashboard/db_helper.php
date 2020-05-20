<?php

function db_connect() {
    $servername = "remotemysql.com";
    $username = "g1nomYxqFk";
    $password = "24STCXaUv6";
    //port 3306
    // Create connection
    $conn = new mysqli($servername, $username, $password, 'g1nomYxqFk');
    
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
    $depo++;
    $sql = "UPDATE general SET deposits=$depo";

    if (!$conn->query($sql) === TRUE) {
        echo "Error updating record: " . $conn->error;
    }
    $conn->close();
}

function deposit($jsonobj){
    $decoded= json_decode($jsonobj);
    $A = $decoded->a;
    $B = $decoded->b;
    $C = $decoded->c;

    $conn = db_connect();
    $sql = "INSERT INTO deposit (a_deposited, b_deposited, c_deposited, date) VALUES ($A, $B, $C, CURRENT_DATE )";
    if (!$conn->query($sql) === TRUE) {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }

    $wheight = $A + $B + $C;
    $sql = "SELECT weight, deposits, wheight_max FROM general";
    $result = $conn->query($sql);
    
    if ($result->num_rows > 0) {
        $row = $result->fetch_assoc();
    } else {
        exit('error');
    }
    $wheight += $row['weight'];
    $deposits = $row['deposits'];
    $wheight_max = $row['wheight_max'];
    $deposits++;
    $sql = "UPDATE general SET weight = $wheight, deposits = $deposits";

    if (!$conn->query($sql) === TRUE) {
        echo "Error updating record: " . $conn->error;
    }
    //controls if the wheight is too much
    if($wheight>$wheight_max){
        $sql = "UPDATE general SET available = 0";

        if (!$conn->query($sql) === TRUE) {
            echo "Error updating record: " . $conn->error;
        }
    }
    $conn->close();
}

function set_avail($avail){
    $conn = db_connect();

    $sql = "UPDATE general SET available = $avail";
    if (!$conn->query($sql) === TRUE) {
        echo "Error updating record: " . $conn->error;
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

function get_a(){
    $conn = db_connect();
    $a_trash = array();
    $sql = "SELECT a_deposited, date FROM deposit ORDER BY deposit_id DESC LIMIT 25";
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
    $sql = "SELECT b_deposited, date FROM deposit ORDER BY deposit_id DESC LIMIT 25";
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
    $sql = "SELECT c_deposited, date FROM deposit ORDER BY deposit_id DESC LIMIT 25 ";
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

function check_pass($pass){
    $conn = db_connect();
    $sql = "SELECT password FROM general";
    $result = $conn->query($sql);
    if ($result->num_rows > 0) {
        if($row = $result->fetch_assoc()) {
            $conf_pass = $row["password"];
        }
        $conn->close();
        if($pass == $conf_pass){
            return true;
        }   
    } else {
        return false;
    }
}


function set_trash_type($json){
    //set_avail(0);
    $obj = json_decode($json);
    $conn = db_connect();
    $sql = "INSERT INTO deposit (deposit_id, a_deposited, b_deposited, c_deposited, date, tmp_deposit) VALUES (NULL,'0', '0', '0', CURRENT_DATE ,'$obj->type')";
    if (!$conn->query($sql) === TRUE) {
        echo "Error: " . $sql . "<br>" . $conn->error;
        return false;
    }
    return true;
}

function deposit_fix($json){
    $obj = json_decode($json);
    $quantity = $obj->quantity;
    $conn = db_connect();
    $trash;
    $id;
    $wheight_control=0;
    $sql_control  = "SELECT a_deposited, b_deposited,c_deposited FROM deposit ORDER BY deposit_id DESC LIMIT 1";
    $result_control = $conn->query($sql_control);
    if ($result_control->num_rows > 0) {
        if($row = $result_control->fetch_assoc()) {
            $wheight_control = $row["a_deposited"] +  $row["b_deposited"] + $row["c_deposited"];
        }
    }
    if ($wheight_control == 0){
        $sql = "SELECT deposit_id, tmp_deposit FROM deposit ORDER BY deposit_id DESC LIMIT 1";
        $result = $conn->query($sql);
        if ($result->num_rows > 0) {
            if($row = $result->fetch_assoc()) {
                $trash = $row["tmp_deposit"];
                $id = $row["deposit_id"];
            }
        }
    
        $sql1 = "UPDATE deposit SET ".$trash."_deposited = '$quantity' WHERE deposit_id = ".$id;
        if (!$conn->query($sql1) === TRUE) {
        }
    }
    $conn->close();
    inc_depsits();
}

function clean_empty_rows(){
    $obj = json_decode($json);
    $conn = db_connect();
    $sql = "DELETE FROM deposit WHERE a_deposited + b_deposited + c_deposited =0";
    if (!$conn->query($sql) === TRUE) {
        echo "Error: " . $sql . "<br>" . $conn->error;
        return false;
    }
    return true;
}
?>
