<?php
include "conexionPDO.php";
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a><br>";
$ref=$_POST["referencia"];
$descripcion=$_POST["descrip"];
$imp=$_POST["imp"];
$ganancia=$_POST["ganancia"];


$SentenciaSQL=("insert into repuestos(Referencia,Descripcion,Importe,Ganancia) values ('$ref','$descripcion','$imp','$ganancia')");

$result = $conexion->query($SentenciaSQL);
if(!$result){
	echo"<br>Error al introducir el repuesto en la Base de Datos";
}else{
	echo"<br>El repuesto se ha introducido con &eacute;xito en la base de datos<br>
	<a href='gestion_repuestos.php'><input type=button value=Volver></a>";
}
