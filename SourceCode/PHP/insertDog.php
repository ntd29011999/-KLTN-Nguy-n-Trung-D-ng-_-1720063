<?php
    require "dbcon.php";

    $ten = $_POST['ten'];
    $ngay = $_POST['ngay'];
    $mau = $_POST['mau'];
    $mota = $_POST['mota'];
    
    $query = "INSERT INTO dog VALUES (NULL, '$ten', '$ngay', '$mau', '$mota')";

    if (mysqli_query($connect, $query)){
        // thanh cong
        echo "success";
    }else {
        echo "error";
    }

?>