<?php
    require "dbcon.php";
    $id = $_POST['id'];
    $query = "DELETE FROM `dog` WHERE id='$id'";
    if (mysqli_query($connect, $query)){
        // thanh cong
        echo "success";
    }else {
        echo "error";
    }

?>