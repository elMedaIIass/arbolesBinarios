README – Equipo B (Árboles Binarios)
======================================

Actividad: Diseña y Compara – Estructuras de Datos
Unidad V: Árboles Binarios
Profesor: Joam Manuel Rincón Zuluaga
Integrantes (Equipo B):
- MADRID PEREZ MARIA JOSE (24110499)
- MARTINEZ QUIROZ CARLOS IGNACIO (24110486)
- MEDELLIN RODRIGUEZ ALEJANDRO (24110829)
- OSORNIO SANCHEZ JUAN JOSE (13311853)
- RODRIGUEZ RODRIGUEZ VICTOR HUGO (24110480)

Contenido
---------
codigo/
  - arbol_cpp.cpp         (ABB manual + comparación con std::set)
  - arbol_python.py       (ABB manual + referencia con lista ordenada + bisect)
documentacion/
  - dataset_nombres.txt   (dataset común)
  - README.txt            (este archivo)
presentacion/
  - presentacion.pptx     (10 diapositivas, enfoque en ABB)
ejecutables/
  - demo_ejecutable.py    (corre PoC/benchmarks de árboles en Python)

Cómo ejecutar
-------------
C++:
  cd codigo
  g++ -O2 -std=c++17 arbol_cpp.cpp -o arbol_cpp
  ./arbol_cpp

Python:
  cd ejecutables
  python3 demo_ejecutable.py

Qué mostrar en la PoC
---------------------
- Inserción del dataset de nombres en el ABB.
- Recorridos (inorden, preorden, postorden) mostrando orden alfabético.
- Búsqueda de un contacto (p. ej. 'Laura') y eliminación (p. ej. 'Diego').
- Comparación de rendimiento: insertar 1000 elementos y búsqueda:
  * C++: ABB manual vs std::set
  * Python: ABB manual vs lista ordenada + bisect

Notas para la presentación (27 de agosto)
-----------------------------------------
- Explicar brevemente Pilas/Colas (del otro equipo) para cumplir el requisito,
  con 1 diapositiva-resumen (incluida).
- Enfatizar: diferencia clave entre ABB no balanceado y estructuras balanceadas
  (std::set ~ árbol rojo-negro).

Entrega final
-------------
- Exportar la PPT a PDF.
- Incluir capturas de pantalla de la ejecución (opcional).
- Agregar a este README los tiempos reales obtenidos.
