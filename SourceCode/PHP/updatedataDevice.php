<?php
    require "dbcon.php";

    $battat = $_POST['battat'];
    $chedo = $_POST['chedo'];
    $led = $_POST['led'];
    // $query = "UPDATE device SET battat='$battat',chedo='$chedo' WHERE id=1";
    $query = "UPDATE device SET battat='$battat', chedo='$chedo', led='$led' WHERE id=1";
    if (mysqli_query($connect, $query)){
        // thanh cong
        echo "success";

    }else {
        echo "error";
    }

?>