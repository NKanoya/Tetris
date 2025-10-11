'use strict'

async function initializeWasm(getModuleFunction) {
    const Module = await getModuleFunction();
    if(Module){
        console.log("Module is loaded sucessfully!");
    }
    return Module;
}

let operationInterface = null;

const opMap = {
    none: 0,
    left: 1,
    right: 2,
    down: 3,
    drop: 4,
    rotateCW: 5,
    rotateCCW: 6
};

export function startTetrisLogic(getModule) {
    initializeWasm(getModule).then(Module => {
        operationInterface = Module.cwrap('do_operation', 'number', ['number']);
        console.log("C Function is successfully wrapped!");

        document.addEventListener('keydown', (event) => {
            switch (event.key) {
                case 'a':
                    operationInterface(opMap.left);
                    console.log(132);
                    break;
                case 'd':
                    operationInterface(opMap.right);
                    break;
                case 's':
                    operationInterface(opMap.drop);
                    break;
                case 'q':
                    operationInterface(opMap.rotateCCW);
                    break;
                case 'e':
                    operationInterface(opMap.rotateCW);
                    break;
            }

            event.preventDefault();
        });

        Module.ccall('JS_process_loop', null, [], []);
        console.log("Start process Loop successfully!");

    });
}