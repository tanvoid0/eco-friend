<?php
	$h = isset($_POST['h']) ? $_POST['h']: NULL;
	$m = isset($_POST['m']) ? $_POST['m']: NULL;
	$l = isset($_POST['l']) ? $_POST['l']: NULL;
	$t = isset($_POST['t']) ? $_POST['t']: NULL;
	

	$servername = "localhost";
	$username = "root";
	$password = "";
	$dbname = "ecofriend";

	// Create connection
	$conn = mysqli_connect($servername, $username, $password, $dbname);
	// Check connection
	if (!$conn) {
	    die("Connection failed: " . mysqli_connect_error());
	}

	$sql = "INSERT INTO data (plant_id, h, m, l, t)
	VALUES (1 ,'$h', '$m', '$l', '$t')";
	// echo $sql;

	if (mysqli_query($conn, $sql)) {
	    echo "New record Inserted!";
	} else {
	    echo "Error: " . $sql . "<br>" . mysqli_error($conn);
	}

	mysqli_close($conn);
?>