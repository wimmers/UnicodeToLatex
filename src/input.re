/* Util */
let str = ReasonReact.stringToElement;

let valueFromEvent = (evt) : string => (
  evt
  |> ReactEventRe.Form.target
  |> ReactDOMRe.domElementToObj
)##value;

/* Types */
type state = string;

let component = ReasonReact.reducerComponent("Input");

let make = (~onSubmit, _) => {
    ...component,
    initialState: () => "",
    reducer: (newText, _text) => {onSubmit(newText); ReasonReact.Update(newText)},
    render: ({state: text, reduce}) =>
    <textarea
        value=text
        _type="text"
        cols=40
        rows=5
        placeholder="Your Unicode Text"
        onChange=(reduce((evt) => valueFromEvent(evt)))
    />
}