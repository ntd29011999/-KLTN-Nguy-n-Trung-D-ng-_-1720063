<?php
    require "dbcon.php";


    $query = "SELECT * FROM `device` ORDER BY id DESC LIMIT 1";
    $data = mysqli_query($connect, $query);
    

    //du lieu
class device{
    function device ($id,$battat, $chedo, $led){
        $this->id = $id;
        $this->battat = $battat;
        $this->chedo = $chedo;
        $this->led = $led;
    }
}
// tao mang
$mangdevice = array();
// them mang 
while($row = mysqli_fetch_assoc($data)){
    array_push($mangdevice, new device($row['id'],$row['battat'],$row['chedo'],$row['led']));
}

echo json_encode($mangdevice);
?>