<!DOCTYPE html>
<html>

    <head>

        <!--Adding title if it was rendered-->
        <?php if (isset($title)): ?>
            <title>Attendo : <?php  echo $title;?></title>
        <?php else: ?>
            <title>Attendo</title>
        <?php endif ?>

        <link href = "/css/styles.css" rel="stylesheet"/>
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
    </head>

    <body>
        <div class = "container">

              <div id = "top">
                      <div>
                          <a href="/"><img src = "img/site_img/logo.jpg" height="10%" width="10%"/></a>
                          </br><?php echo "Date: ".date('d-m-Y');?>
                      </div>
                      <div>
                      <ul class="nav nav-pills">
<?php if(!empty($_SESSION['tid'])): ?>

<?php if(!empty($_SESSION["class"])) : ?>
                      <li><button class="btn btn-primary dropdown-toggle" type="button"><a href="classes.php" style="color:white;text-decoration: none;"><?php echo strtoupper($_SESSION["class"]);?></a></button></li>
                      <li><button class="btn btn-primary dropdown-toggle" type="button"><a href="attendence_viewer.php" style="color:white;text-decoration: none;">ATTENDENCE VIEW</a></button></li>
<?php else:?>
                      <li><button class="btn btn-primary dropdown-toggle" type="button"><a href="classes.php" style="color:white;text-decoration: none;">CLASSES</a></button></li>
<?php endif?>

                      <li><button class="btn btn-primary dropdown-toggle" type="button"><a href="add_class.php" style="color:white;text-decoration: none;">ADD CLASS</a></button></li>
                      <li><button class="btn btn-primary dropdown-toggle" type="button"><a href="classes.php" style="color:white;text-decoration: none;"><?php echo "WELCOME ".strtoupper($_SESSION["t_name"]);?></a></button></li>
                      <li><button class="btn btn-primary" type="button"><a href="logout.php" style="color:white;text-decoration: none;">LOGOUT</a></li>

<?php endif?>
                  </ul>

                  </div>
              </div>
              <div id = "middle">