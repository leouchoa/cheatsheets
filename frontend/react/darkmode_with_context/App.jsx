import Page from './Page';
import ThemeContextProvider from "./ThemeContextProvider.jsx";


function App() {
  return (
    <ThemeContextProvider>
      <Page />
    </ThemeContextProvider>
  );
}

export default App;

