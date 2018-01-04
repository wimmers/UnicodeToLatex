/* Imports */
/* open Flags; */

/* Util */
let str = ReasonReact.stringToElement;
let to_js_bool = Js.Boolean.to_js_boolean;

/* Types */
type state = {
  text: string,
  bindings: string,
  flags: Flags.flag_state,
};

type action =
  | UpdateText(string)
  | UpdateBindings(string)
  | ToggleFlag(Flags.flag);

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
  initialState: () => {text: "", bindings: "", flags: Flags.initial_flags},
  reducer: (action: action, state: state) => switch action {
    | UpdateText(text) => ReasonReact.Update({...state, text})
    | UpdateBindings(bindings) => ReasonReact.Update({...state, bindings})
    | ToggleFlag(flag) => ReasonReact.Update({...state, flags: Flags.toggleFlag(flag, state.flags)}) 
  },
  render: ({reduce, state, handle}) => {
    let hide_debug = !Flags.flagSet(Debug, state.flags);
    let hide_debug_js = to_js_bool(hide_debug);
    let hide_settings = !Flags.flagSet(Show_Settings, state.flags);
    let hide_settings_js = to_js_bool(hide_settings);
    let onToggle = (flag) => reduce(() => ToggleFlag(flag));
    <div className="app">
    <div className="title"> (str("Unicode To Latex")) </div>
    <Input
      onSubmit=(reduce((text) => UpdateText(text)))
      placeholder="Your Unicode Text"
    />
    <div className="settings" hidden=hide_settings_js>
    <div
      onClick=((_evt) => onToggle(Show_Settings)())
    >
      (str(hide_settings ? "+ Settings" : "- Settings"))
    </div>
    <FlagBox
      flag=Whitespace
      title="Protect Whitespace"
      flags=state.flags hidden=hide_settings onToggle
    />
    <FlagBox
      flag=Isabelle_Keywords
      title="Replace Isabelle Keywords"
      flags=state.flags  hidden=hide_settings onToggle
    />
    <FlagBox
      flag=Remove_Quotations
      title="Remove Quotation Marks"
      flags=state.flags hidden=hide_settings onToggle
    />
    <FlagBox
      flag=Fallback
      title="Use Fallback Replacements"
      flags=state.flags hidden=hide_settings onToggle
    />
    <FlagBox
      flag=Debug
      title="Show Debug Output"
      flags=state.flags hidden=hide_settings onToggle
    />
    <span className="caption" hidden=hide_settings_js> (str("Your Substitutions")) </span>
    <Input
      onSubmit=(reduce((text) => UpdateBindings(text)))
      placeholder="replace : with"
      hidden=hide_settings
    />
    </div>
    <h3 className="caption"> (str("Latex Output")) </h3>
    <pre className="output"> (str(Translate.translate(state.flags, state.text, state.bindings))) </pre>
    <div className="debug" hidden=hide_debug_js>
      <h4 className="caption" hidden=hide_debug_js> (str("Debug")) </h4>
      <pre className="output" hidden=hide_debug_js> (str(state.text)) </pre>
    </div>
    </div>
  }
};
