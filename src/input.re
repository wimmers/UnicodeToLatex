/* Imports */
open Util;

/* Types */
type state = string;

let component = ReasonReact.reducerComponent("Input");

let make = (~onSubmit, ~placeholder, ~hidden=false, _children) => {
  ...component,
  initialState: () => "",
  reducer: (newText, _text) => {
    onSubmit(newText);
    ReasonReact.Update(newText);
  },
  render: ({state: text, reduce}) =>
    hidden ?
      ReasonReact.nullElement :
      <textarea
        value=text
        _type="text"
        cols=40
        rows=5
        placeholder
        onChange=(reduce(evt => valueFromEvent(evt)))
      />
};