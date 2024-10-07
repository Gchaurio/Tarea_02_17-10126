import * as THREE from 'three';

const scene = new THREE.Scene();
scene.background = new THREE.Color(0x2D2B2B);
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
camera.position.z = 1.5;

const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);

const vertices = new Float32Array([-0.5, 0, 0, 0.5, 0, 0, 0, 0.87, 0]);
const colors = new Float32Array([1, 0, 0, 0, 1, 0, 0, 0, 1]);

const geometry = new THREE.BufferGeometry();
geometry.setAttribute('position', new THREE.BufferAttribute(vertices, 3));
geometry.setAttribute('color', new THREE.BufferAttribute(colors, 3));

const material = new THREE.MeshBasicMaterial({vertexColors: true});

const triangle = new THREE.Mesh(geometry, material);
scene.add(triangle);

function animate() {
    renderer.render(scene, camera);
}

renderer.setAnimationLoop(animate);


