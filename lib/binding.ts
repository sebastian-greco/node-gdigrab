const addon = require('../build/Release/node-gdigrab-native');

interface INodeGdigrabNative
{
    greet(strName: string): string;
    grab(): Buffer;
};

class NodeGdigrab {
    constructor(name: string) {
        this._addonInstance = new addon.NodeGdigrab(name)
    }

    greet (strName: string) {
        return this._addonInstance.greet(strName);
    }

    grab () {
        return this._addonInstance.grab();
    }

    // private members
    private _addonInstance: INodeGdigrabNative;
}

export = NodeGdigrab;
