type person = {
  fullName: string,
  id: int
};

let component = ReasonReact.statelessComponent("Person");

let getBg = (selected: bool) => selected ? "#f00" : "#0f0";

let make = (~person: person, ~selected: bool, _children) => {
  ...component,
  render: _self =>
    <div
      style=(
        ReactDOMRe.Style.make(
          ~color="#444444",
          ~fontSize="68px",
          ~backgroundColor=getBg(selected),
          ()
        )
      )>
      (ReasonReact.stringToElement(person.fullName))
    </div>
};