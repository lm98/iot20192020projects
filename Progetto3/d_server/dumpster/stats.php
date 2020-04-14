<?php

include 'db_helper.php';

$dataPoints1 = get_a();
$dataPoints2 = get_b();
$dataPoints3 = get_c();
?>
<!DOCTYPE HTML>
<html>
<head>  
<link rel="stylesheet" type="text/css" href="style2.css">
<script>
window.onload = function () {
 
var chart = new CanvasJS.Chart("chartContainer", {
	animationEnabled: true,
	theme: "light2",
	title:{
		text: "History of the dumps."
	},
	legend:{
		cursor: "pointer",
		verticalAlign: "center",
		horizontalAlign: "right",
		itemclick: toggleDataSeries
	},
	data: [{
		type: "column",
		name: "A type trash",
		indexLabel: "{y}",
		yValueFormatString: "kg #0.##",
		showInLegend: true,
		dataPoints: <?php echo json_encode($dataPoints1, JSON_NUMERIC_CHECK); ?>
	},{
		type: "column",
		name: "B type trash",
		indexLabel: "{y}",
		yValueFormatString: "kg #0.##",
		showInLegend: true,
		dataPoints: <?php echo json_encode($dataPoints2, JSON_NUMERIC_CHECK); ?>
	},{
		type: "column",
		name: "C type trash",
		indexLabel: "{y}",
		yValueFormatString: "kg #0.##",
		showInLegend: true,
		dataPoints: <?php echo json_encode($dataPoints3, JSON_NUMERIC_CHECK); ?>
	}]
});
chart.render();
 
function toggleDataSeries(e){
	if (typeof(e.dataSeries.visible) === "undefined" || e.dataSeries.visible) {
		e.dataSeries.visible = false;
	}
	else{
		e.dataSeries.visible = true;
	}
	chart.render();
}
 
}
</script>
</head>
<body>
<div id="chartContainer" style="height: 370px; width: 100%;"></div>
<script src="https://canvasjs.com/assets/script/canvasjs.min.js"></script>
<br/>
<a href="index.php">Click here to go back to the main page</a>
</body>
</html> 