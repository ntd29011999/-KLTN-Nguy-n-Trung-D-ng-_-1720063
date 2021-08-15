<?php
    require "dbcon.php";


    $query = "SELECT * FROM `account`";
    $data = mysqli_query($connect, $query);
    

    //du lieu
class account{
    function account ($id,$phone, $password, $deviceid){
        $this->id = $id;
        $this->phone = $phone;
        $this->password = $password;
        $this->deviceid = $deviceid;
    }
}
// tao mang
$mangaccount = array();
// them mang 
while($row = mysqli_fetch_assoc($data)){
    array_push($mangaccount, new account($row['id'],$row['phone'],$row['password'],$row['device_id']));
}

echo json_encode($mangaccount);
?>