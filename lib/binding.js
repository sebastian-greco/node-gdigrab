const addon = require('../build/Release/node-gdigrab-native');
;
class NodeGdigrab {
    constructor(name) {
        this._addonInstance = new addon.NodeGdigrab(name);
    }
    greet(strName) {
        return this._addonInstance.greet(strName);
    }
    grab() {
        return this._addonInstance.grab();
    }
}
export default NodeGdigrab;
