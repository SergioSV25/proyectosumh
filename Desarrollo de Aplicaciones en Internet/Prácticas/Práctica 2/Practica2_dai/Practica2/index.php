<?php
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br>";
?>
<html>
<head>
<body>
<h2>Indice Pagina Principal</h2>
<a href="gestion_clientes.php"><input type=button value="Gestion Clientes"></a>
<a href="gestion_motos.php"><input type=button value="Gestion Motos"></a>
<a href="gestion_repuestos.php"><input type=button value="Gestion Repuestos"></a>
<a href="gestion_facturas.php"><input type=button value="Gestion de Facturas"></a>

<br><br>

<a href="filtro_clientes.php"><input type=button value="Consultar Clientes"></a>
<a href="Consulta_Factura.php"><input type=button value="Consultar Facturas"></a>





</body>
</head>
</html>