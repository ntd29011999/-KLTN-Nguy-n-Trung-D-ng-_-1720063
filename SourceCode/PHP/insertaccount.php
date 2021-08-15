<?php
    require "dbcon.php";

    $phone = $_POST['phone'];
    $password = $_POST['password'];
    $deviceid = $_POST['deviceid'];
    
    $query = "INSERT INTO account VALUES (NULL, '$phone', '$password', '$deviceid')";

    if (mysqli_query($connect, $query)){
        // thanh cong
        echo "success";

    }else {
        echo "error";
    }

?>