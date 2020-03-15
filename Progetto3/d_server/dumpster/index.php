<?php
include 'db_helper.php';

$avail = is_available();

if ($avail){
    $state=' available';
    $nstate= 'unavailable';
 } else {
    $state=' unavailable';
    $nstate= 'available';

 }

$deposits = get_deposits();
?>

<!DOCTYPE html>
<html>
<head>
<link rel="stylesheet" type="text/css" href="mystyle.css">
</head>
<body>

<h1>Dumpster Server</h1>

<h2>Numero di depositi:</h2>
<p><?php echo $deposits; ?></p>

<h2>Dumpster is now <?php echo $state;?> </h2>

<?php
if ($avail){
    require('set_unavailable.html');
}
?>

<?php
//per ora utile ma poi andra' tolta
if (!$avail){
    require('set_available.html');
}
?>
</body>
</html>