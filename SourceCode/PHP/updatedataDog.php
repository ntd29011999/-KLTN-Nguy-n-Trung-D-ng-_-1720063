<?php
    require "dbcon.php";
    $id = $_POST['id'];
    $ngay = $_POST['ngay'];
    
    $query = "UPDATE dog SET ngay='$ngay' WHERE id='$id'";
    if (mysqli_query($connect, $query)){
        // thanh cong
        echo "success";
    }else {
        echo "error";
    }

?>