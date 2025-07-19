import { connect } from "react-redux";
import store from "./store";
function APP() {
  return (
    <div>
      <div>
        <button
          aria-label="Increment value"
          onClick={() => store.dispatch({ type: "INCREMENT" })}
        >
          Increment
        </button>
        <span>{store.getState().value}</span>
        <button
          aria-label="Decrement value"
          onClick={() => store.dispatch({ type: "DECREMENT" })}
        >
          Decrement
        </button>
      </div>
    </div>
  );
}
const mapStateToProps = (state) => ({
  count: state,
});

const mapDispatchToProps = (dispatch) => ({
  onIncrement: () => dispatch({ type: "INCREMENT" }),
  onDecrement: () => dispatch({ type: "DECREMENT" }),
});
export default connect(mapStateToProps, mapDispatchToProps)(APP);
