<?php
    require "dbcon.php";
    $query = "SELECT * FROM `dog`";
    $data = mysqli_query($connect, $query);
    //du lieu
class dog{
    function dog ($id,$ten, $ngay,$mau,$mota){
        $this->id = $id;
        $this->ten = $ten;
        $this->ngay = $ngay;
        $this->mau = $mau;
        $this->mota = $mota;
    }
}
// tao mang
$mangdog = array();
// them mang 
while($row = mysqli_fetch_assoc($data)){
    array_push($mangdog, new dog($row['id'],$row['ten'],$row['ngay'],$row['mau'],$row['mota']));
}

echo json_encode($mangdog);
?>