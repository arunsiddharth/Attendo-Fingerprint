<?php
    //https://ide50-arun-siddharth.cs50.io/enroll.php?tid=game&cname=Wireless&id=0&sid=2015uec1283
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
                $sid=$_GET['sid'];
                $id=$_GET['id'];
                $query = "SELECT * FROM class WHERE cname = '".$cname."'";
                echo $query;
                $results = $conn ->query($query);
                $row = $results->fetch_assoc();
                $cid = $row['cid'];

                //add to db
                $query = "INSERT INTO student(sid,id,cid) VALUES('".$sid."', '".$id."', ".$cid.")";
                echo $query;
                $results = $conn->query($query);
                if($results != 1){
                    apologize("Student Already Present");
                }
                else{
                    $query = "UPDATE class SET count=count+1 WHERE cid=".$cid;
                    $conn->query($query);
                }
    }
?>