type prize = {
  name: string,
  assignedTo: option(int)
};

let component = ReasonReact.statelessComponent("Person");

let make = (~prize: prize, ~beingRaffled: bool, _children) => {
  ...component,
  render: _self =>
    <div
      style=(
        ReactDOMRe.Style.make(
          ~color=beingRaffled ? "#444" : "#aaa",
          ~fontSize="42px",
          ()
        )
      )>
      (ReasonReact.stringToElement(prize.name))
    </div>
};