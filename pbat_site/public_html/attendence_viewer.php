<?php
    include("../include/config.php");
    include("../include/helpers.php");

    if($_SERVER['REQUEST_METHOD']=="GET"){
        $conn=dbconnect();
        if($conn->connect_error){
				die("Connection Failed".$conn->conncet_error);
		}
        else{
            $class = $_SESSION['class'];
            $query = "SELECT * FROM class WHERE cname = '".$_SESSION['class']."'";
            $results = $conn->query($query);
            $row = $results->fetch_assoc();
            $cid = $row['cid'];
            $query = "SELECT * FROM student WHERE cid=".$cid;
            $results = $conn->query($query);
            include("../views/header.php");
            echo student_printer($results);
            include("../views/footer.php");
        }
    }
?>