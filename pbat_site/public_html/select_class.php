<?php
    include("../include/config.php");
    include("../include/helpers.php");
    if($_SERVER['REQUEST_METHOD']=="GET"){
        $_SESSION['class']=$_GET['class'];
    }
    redirect("attendence_viewer.php");
?>