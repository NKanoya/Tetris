'use strict'

const constructMatrix = () => {
    const matrixContainer = document.getElementById('tetris-matrix');

    for(let row = 4; row < 22; ++row) {
        for(let col = 0; col < 10; ++col) {
            const block = document.createElement('div');
            block.className = 'tetris-matrix-block';
            block.id = 'matrix-block-' + row + '-' + col;
            block.style.backgroundColor = 'transparent';
            matrixContainer.appendChild(block);
        }
    }
};

constructMatrix();
