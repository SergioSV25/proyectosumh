<?php
include("ConexionPDO.php");
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a><br>";

	$sql = "SELECT * from clientes order by id_cliente";
	$result = $conexion->query($sql);
	
	$rows = $result->fetchALL();

	foreach($rows as $row){
		$id_cliente =$row['Id_Cliente'];
		$dni = $row['DNI'];
		$nombre = $row['Nombre'];
		$apellido1 = $row['Apellido1'];
		$apellido2 = $row['Apellido2'];
		$direccion = $row['Direccion'];
		$cp = $row['CP'];
		$poblacion = $row['Poblacion'];
		$provincia = $row['Provincia'];
		$telefono = $row['Telefono'];
		$email = $row['Email'];
		
		echo "<table border=1><tr><td><center><b>$id_cliente</b></center></td>
		<td>$dni</td>
		<td>$nombre</td>
		<td>$apellido1</td>
		<td>$apellido2</td>
		<td>$direccion</td>
		<td>$cp</td>
		<td>$poblacion</td>
		<td>$provincia</td>
		<td>$telefono</td>
		<td>$email</td>
		<
		</tr></table>";
		
	}
	


?>