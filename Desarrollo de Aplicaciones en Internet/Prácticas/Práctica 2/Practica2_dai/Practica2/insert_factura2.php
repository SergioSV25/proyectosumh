<?php
include "conexionPDO.php";
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a>";
$numero_factura=$_POST["nfact"];
$matricula=$_POST["matricula"];
$mano_obra=$_POST["mobra"];
$precio_hora=$_POST["phora"];
$fecha_emision=$_POST["femision"];
$fecha_pago=$_POST["fpago"];

for($i=0;isset($_POST["referencia"][$i]);$i++)
{
	$referencia = $_POST["referencia"][$i];
	$unidades = $_POST["unidades"][$i];
}

$consulta = "INSERT detalle_factura(Numero_Factura,Referencia, Unidades) VALUES ($numero_factura,$referencia,$unidades)";
$conexion->query($consulta);

$sentencia = "SELECT Importe, Ganancia FROM repuestos WHERE Referencia = '$referencia'";
$resultado = $conexion->query($sentencia)->fetch();

$importe = $resultado['Importe'];
$ganancia = $resultado['Ganancia'];

$coste_piezas = $unidades*$importe;

$base_imponible = $coste_piezas + ($mano_obra * $precio_hora);
$iva = $base_imponible * 0.21;
$total = $base_imponible + $iva;


$SentenciaSQL=("insert into facturas(Numero_Factura,Matricula,Mano_obra,Precio_Hora,Fecha_Emision,Fecha_Pago,Base_Imponible, IVA, Total) values ('$numero_factura','$matricula','$mano_obra','$precio_hora','$fecha_emision','$fecha_pago','$base_imponible','$iva','$total')");

$result = $conexion->query($SentenciaSQL);
if(!$result){
	echo"<br>Error al introducir el repuesto en la Base de Datos";
}else{
	echo"<br>La factura se ha introducido con éxito
	<a href='gestion_facturas.php'>Volver</a>";
}
