import httpCommon from "../http-common";

const min = (id, amount) => {
    return httpCommon.post("api/saving/min", { id, amount });
};

const history = (id,great) => {
    return httpCommon.post("api/saving/history",{ id, great });
}

const periodic = (id,deposit,entry,periodic) => {
    return httpCommon.post("api/saving/periodic",{ id, deposit, entry, periodic});
}

const relation = (id,amount) => {
    return httpCommon.post("api/saving/relation",{ id, amount});
}

const out = (id,max) => {
    return httpCommon.post("api/saving/out",{ id, max});
}

export default { min, history, periodic, relation, out };