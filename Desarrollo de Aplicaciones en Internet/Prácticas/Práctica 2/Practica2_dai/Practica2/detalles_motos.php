<?php
include "conexionPDO.php";
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a>";	

	$matricula=$_GET["matricula"];
	
	$sql = "SELECT * FROM motocicletas where Matricula='$matricula'";
	$result = $conexion->query($sql);
	$rows = $result->fetchALL();
	
	foreach($rows as $row){
		$id=$row['Id_Cliente'];
		$marca = $row['Marca'];
		$modelo = $row['Modelo'];
		$anyo = $row['Anyo'];
		$color = $row['Color'];
	}
	
	$sqlcliente = "SELECT * from clientes";
	$consulta = $conexion->prepare($sqlcliente);
	$consulta->execute();
	$resultcliente = $consulta->fetchAll();
	

	echo " <form method=post action=modificar_motos.php> 
		Propietario: <select name='id'>";
	
	foreach($resultcliente as $fila){
		$idcliente =$fila['Id_Cliente'];
		$nombre = $fila['Nombre'];
		$apellido1 = $fila['Apellido1'];
		$apellido2 = $fila['Apellido2'];

		$cliente = $nombre . " " . $apellido1 . " " . $apellido2;
			
		if($idcliente == $id){
			echo "<option value=$idcliente selected>$cliente</option>";
				
		}else{
			echo "<option value=$idcliente>$cliente</option>";
		}
	}
		echo "</select>
		<br>Matricula:
		<input type=text name=matricula readonly value=$matricula>
		<br>Marca:
		<input type=text name=marca value=$marca>
		<br>Modelo:
		<input type=text name=modelo value=$modelo>
		<br>Anyo:
		<input type=text name=anyo value=$anyo>

		<br>Color:
		<input type=text name=color value=$color>";
		


?>
<input type=submit value=Modificar>
</form>