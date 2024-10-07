  // Importa la biblioteca Three.js
import * as THREE from 'three';

// Crear la escena donde se añadirán los objetos 3D
const scene = new THREE.Scene();
scene.background = new THREE.Color(0x2D2B2B);  // Establecer el color de fondo de la escena

// Configurar la cámara en perspectiva
// FOV (75 grados), proporción (aspect ratio) igual al tamaño de la ventana, plano cercano a 0.1 y plano lejano a 1000
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);

// Posicionar la cámara más lejos para ver los objetos en escena
camera.position.z = 1.5;  

// Crear el renderer WebGL y establecer su tamaño al tamaño de la ventana
const renderer = new THREE.WebGLRenderer();
// Ajustar el tamaño del renderer
renderer.setSize(window.innerWidth, window.innerHeight);
// Añadir el renderer al documento HTML para visualizarlo
document.body.appendChild(renderer.domElement);

// Definir los vértices del triángulo en un arreglo de Float32 con las coordenadas de los vertices
const vertices = new Float32Array([-0.5, 0, 0, 0.5, 0, 0, 0, 0.87, 0]);

// Definir los colores correspondientes a cada vértice (rojo, verde, azul)
const colors = new Float32Array([1, 0, 0, 0, 1, 0, 0, 0, 1]);

// Crear la geometría utilizando BufferGeometry, que optimiza el uso de vértices y colores
const geometry = new THREE.BufferGeometry();
// Añadir los vértices y colores como atributo
geometry.setAttribute('position', new THREE.BufferAttribute(vertices, 3));
geometry.setAttribute('color', new THREE.BufferAttribute(colors, 3));

// Crear el material básico que usará los colores de los vértices, habilitandole el uso de color por vertice
const material = new THREE.MeshBasicMaterial({vertexColors: true});

// Crear un mesh que combina la geometría y el material, formando el triángulo
const triangle = new THREE.Mesh(geometry, material);
// Añadir el triángulo a la escena
scene.add(triangle);  

// Función de animación: se llama continuamente para renderizar la escena
function animate() {
    renderer.render(scene, camera);
}

// Iniciar el bucle de animación: esto asegura que la función animate se llame en cada frame
renderer.setAnimationLoop(animate);