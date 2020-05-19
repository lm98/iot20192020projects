<?php
 
$dataPoints1 = array(
	array("label"=> "2010", "y"=> 36.12),
	array("label"=> "2011", "y"=> 34.87),
	array("label"=> "2012", "y"=> 40.30),
	array("label"=> "2013", "y"=> 35.30),
	array("label"=> "2014", "y"=> 39.50),
	array("label"=> "2015", "y"=> 50.82),
	array("label"=> "2016", "y"=> 74.70)
);
$dataPoints2 = array(
	array("label"=> "2010", "y"=> 64.61),
	array("label"=> "2011", "y"=> 70.55),
	array("label"=> "2012", "y"=> 72.50),
	array("label"=> "2013", "y"=> 81.30),
	array("label"=> "2014", "y"=> 63.60),
	array("label"=> "2015", "y"=> 69.38),
	array("label"=> "2016", "y"=> 98.70)
);
	
?>
<!DOCTYPE HTML>
<html>
<head>  
<script>
window.onload = function () {
 
var chart = new CanvasJS.Chart("chartContainer", {
	animationEnabled: true,
	theme: "light2",
	title:{
		text: "Average Amount Spent on Real and Artificial X-Mas Trees in U.S."
	},
	legend:{
		cursor: "pointer",
		verticalAlign: "center",
		horizontalAlign: "right",
		itemclick: toggleDataSeries
	},
	data: [{
		type: "column",
		name: "Real Trees",
		indexLabel: "{y}",
		yValueFormatString: "$#0.##",
		showInLegend: true,
		dataPoints: <?php echo json_encode($dataPoints1, JSON_NUMERIC_CHECK); ?>
	},{
		type: "column",
		name: "Artificial Trees",
		indexLabel: "{y}",
		yValueFormatString: "$#0.##",
		showInLegend: true,
		dataPoints: <?php echo json_encode($dataPoints2, JSON_NUMERIC_CHECK); ?>
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
</body>
</html> 




//////////////////////////////

<?
# ------- The graph values in the form of associative array
$values=array(
    "Jan" => 110,
    "Feb" => 130,
    "Mar" => 215,
    "Apr" => 81,
    "May" => 310,
    "Jun" => 110,
    "Jul" => 190,
    "Aug" => 175,
    "Sep" => 390,
    "Oct" => 286,
    "Nov" => 150,
    "Dec" => 196
);


$img_width=450;
$img_height=300; 
$margins=20;


# ---- Find the size of graph by substracting the size of borders
$graph_width=$img_width - $margins * 2;
$graph_height=$img_height - $margins * 2; 
$img=imagecreate($img_width,$img_height);


$bar_width=20;
$total_bars=count($values);
$gap= ($graph_width- $total_bars * $bar_width ) / ($total_bars +1);


# -------  Define Colors ----------------
$bar_color=imagecolorallocate($img,0,64,128);
$background_color=imagecolorallocate($img,240,240,255);
$border_color=imagecolorallocate($img,200,200,200);
$line_color=imagecolorallocate($img,220,220,220);

# ------ Create the border around the graph ------

imagefilledrectangle($img,1,1,$img_width-2,$img_height-2,$border_color);
imagefilledrectangle($img,$margins,$margins,$img_width-1-$margins,$img_height-1-$margins,$background_color);


# ------- Max value is required to adjust the scale -------
$max_value=max($values);
$ratio= $graph_height/$max_value;


# -------- Create scale and draw horizontal lines  --------
$horizontal_lines=20;
$horizontal_gap=$graph_height/$horizontal_lines;

for($i=1;$i<=$horizontal_lines;$i++){
    $y=$img_height - $margins - $horizontal_gap * $i ;
    imageline($img,$margins,$y,$img_width-$margins,$y,$line_color);
    $v=intval($horizontal_gap * $i /$ratio);
    imagestring($img,0,5,$y-5,$v,$bar_color);

}


# ----------- Draw the bars here ------
for($i=0;$i< $total_bars; $i++){ 
    # ------ Extract key and value pair from the current pointer position
    list($key,$value)=each($values); 
    $x1= $margins + $gap + $i * ($gap+$bar_width) ;
    $x2= $x1 + $bar_width; 
    $y1=$margins +$graph_height- intval($value * $ratio) ;
    $y2=$img_height-$margins;
    imagestring($img,0,$x1+3,$y1-10,$value,$bar_color);imagestring($img,0,$x1+3,$img_height-15,$key,$bar_color);        
    imagefilledrectangle($img,$x1,$y1,$x2,$y2,$bar_color);
}
header("Content-type:image/png");
imagepng($img);
$_REQUEST['asdfad']=234234;

?>