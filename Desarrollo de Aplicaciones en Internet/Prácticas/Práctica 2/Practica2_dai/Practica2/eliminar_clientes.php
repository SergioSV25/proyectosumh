<?php
include("ConexionPDO.php");
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a>";

$array_borrados=$_POST["borrar"];

$error=0;


for($i=0;$i<count($array_borrados);$i++){
	$SentenciaSQL = "Delete from clientes where Id_Cliente='".$array_borrados[$i]."'";
	echo $SentenciaSQL;
	
	$result = $conexion->query($SentenciaSQL);
	
	if(!$result){
		$error=1;
	}
}

if($error==0){
	echo "<br><br>El/Los Cliente(s) se ha(n) eliminado correctamente.";
}

?>

<html>
<head>
	<title>Usuario Eliminado</title>
	<meta charset="UTF-8"/>
</head>
<body>
	<a href=index.php><input type=button value=Inicio></a>
</body>
</html>