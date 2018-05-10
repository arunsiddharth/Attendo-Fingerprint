<?php
    function apologize($message){
        render("apologize.php", ["message" => $message]);
    }

    function redirect($location){
        header("Location: {$location}");
        exit;
    }

    function render($view, $values = []){

        if(file_exists("../views/{$view}")){
            // extract variables into local scope
            extract($values);

            // render view (between header and footer)
            require("../views/header.php");
            require("../views/{$view}");
            require("../views/footer.php");
            exit;
        }

        else{
            trigger_error("Invalid view: {$view}", E_USER_ERROR);
        }
    }

    function logout(){
        //unset session
        $_SESSION = [] ;

        //remove cookie
        if (!empty($_COOKIE[session_name()])){
            setcookie(session_name(),"",time()-42000);
        }

        session_destroy();
        redirect("index.php");
    }

    function student_printer($result){
        //get $result as arrays of rows each row containing same as row of table student write a code get help from class printer
        $final = "<table class = 'table table-stripped'><thead><tr><th>S.no.</th><th>Student ID</th><th>Attendence</th></tr></thead>";
        $i=1;
        while($row = $result ->fetch_assoc()){
            $final = $final ."<tr align = 'left'><td>".$i."</td><td>".$row["sid"]."</td><td>".$row["attendance"]."</td></tr>";
            $i=$i+1;
        }
        if($i==1)return "No Classes were taken by you of this subject";
        $final = $final."</table>";
        return $final;
    }

    function class_printer($result){
        $final = "<table class='table table-striped'><thead><tr><th>Sr. No.</th><th>Class Name</th><th>No. of Students</th><th>GO to Class</th></tr></thead>";
        $i=1;
        while($row = $result->fetch_assoc()){
            $final = $final . "<tr align = 'left'><td>".$i."</td><td>".$row['cname']."</td><td>".$row['count']."<td><a href='select_class.php?class=".$row['cname']."'>GO</a></td></tr>";
            $i=$i+1;
        }
        $final = $final."</table>";
        return $final;
    }

    if (!in_array($_SERVER["PHP_SELF"], ["/login.php", "/logout.php", "/register.php","/enroll.php","/match.php","/index.php"]))
    {
        if (empty($_SESSION["tid"]))
        {
            redirect("login.php");
        }
    }
?>
