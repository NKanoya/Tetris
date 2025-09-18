'use strict'

const constructMatrix = () => {
    const matrixContainer = document.getElementById('tetris-matrix');

    for(let i = 0; i < 10; ++i) {
        for(let j = 0; j < 18; ++j) {
            const block = document.createElement('div');
            block.className = 'tetris-matrix-block';
            block.id = 'matrix-block-' + i + '-' + j;
            matrixContainer.appendChild(block);
        }
    }

};

constructMatrix();