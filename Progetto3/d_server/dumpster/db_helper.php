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
        echo "error";
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
?>