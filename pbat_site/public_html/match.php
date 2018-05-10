<?php
    //https://ide50-arun-siddharth.cs50.io/match.php?tid=game&cname=Wireless&id=0x1x2x
    //enroll.php
    include('../include/config.php');
    include('../include/helpers.php');

    $conn = dbconnect();
    if($conn->connect_error){
        die("CONNECTION FAILED".$conn->conncet_error);
    }
    else{
                $tname=$_GET['tid'];
                $cname=$_GET['cname'];
                $id=$_GET['id'];
                $id_array = explode('x',(string)$id);
                $id_array = array_unique($id_array);
                $query = "SELECT * FROM class WHERE cname = '".$cname."'";
                echo $query;
                $results = $conn ->query($query);
                $row = $results->fetch_assoc();
                $cid = $row['cid'];

                //add to db
                for($i=0;$i<count($id_array);$i++){
                        $query = "UPDATE student SET attendance=attendance+1 WHERE cid=".$cid." AND id='".$id_array[$i]."'";
                        echo $query;
                        $conn->query($query);
                }
    }
?>
