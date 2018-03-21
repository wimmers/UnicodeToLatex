/* Util */
let str = ReasonReact.stringToElement;

let valueFromEvent = evt : string => (
                                       evt
                                       |> ReactEventRe.Form.target
                                       |> ReactDOMRe.domElementToObj
                                     )##value;

let to_js_bool = Js.Boolean.to_js_boolean;