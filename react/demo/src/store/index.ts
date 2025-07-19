import { createStore } from "redux";

const initialState = {
  value: 0,
};
type Action =
  | { type: 'INCREMENT' }
  | { type: 'DECREMENT' }
  | { type: 'INCREMENT_BY_AMOUNT', payload: number };
const reducer = function reducer(state = initialState, action: Action) {
  state = { ...state };
  switch (action.type) {
    case "INCREMENT":
      state.value += 1;
      break;
    case "DECREMENT":
      state.value -= 1;
      break;
    case "INCREMENT_BY_AMOUNT":
      state.value += action.payload;
      break;
    default: break;
  }
  return state;
};
const store = createStore(reducer);

export default store;