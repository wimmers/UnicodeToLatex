/* Util */
let str = ReasonReact.stringToElement;

/* Types */
type state = string;

/* This is the basic component. */
let component = ReasonReact.reducerComponent("Page");

let testText = {|
crel_vs (list_all2 S) (map f xs) (map1⇩T . ⟨f⇩T'⟩ . ⟨ys⟩)
〈

A good day, World!
Schönen Tag, Welt!
Une bonne journée, tout le monde!
يوم جيد، العالم
좋은 일, 세계!
Một ngày tốt lành, thế giới!
こんにちは、世界！世
Γ
|};

let make = (~message, _children) => {
  ...component,
  initialState: () => "",
  reducer: (text: string, _state: string) => {
    ReasonReact.Update(text)
  },
  render: ({reduce, state, handle}) =>
    <div className="app">
    <div className="title"> (str("Unicode To Latex")) </div>
    <Input onSubmit=(reduce((text) => text)) />
    <h4 className="caption"> (str("Latex Output")) </h4>
    <pre className="output"> (str(Translate.translate(state))) </pre>
    <h4 className="caption"> (str("Debug")) </h4>
    <pre className="output"> (str(state)) </pre>
    </div>
};
